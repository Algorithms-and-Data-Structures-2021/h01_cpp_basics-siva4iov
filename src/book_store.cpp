#include "book_store.hpp"

#include <algorithm>  // copy
#include <stdexcept>  // invalid_argument

// 1. реализуйте функцию ...
ResizeStorageStatus resize_storage(Book *&storage, int size, int new_capacity) {
  // здесь мог бы быть ваш разносторонний и многогранный код ...
  // Tip 1: проведите валидацию аргументов функции
  // Tip 2: не забудьте высвободить ранее выделенную память под хранилище
  if (storage == nullptr) {
      return ResizeStorageStatus::NULL_STORAGE;
  }
  if ((new_capacity <= BookStore().GetCapacity()) or (new_capacity <= size)) {
      return ResizeStorageStatus::INSUFFICIENT_CAPACITY;
  }
  if (size < 0) {
      return ResizeStorageStatus::NEGATIVE_SIZE;
  }
  Book *new_storage = new Book[new_capacity];
  std::copy(storage, storage + size, new_storage);
  delete [] storage;
  storage = new_storage;

  return ResizeStorageStatus::SUCCESS;
}

// 2. реализуйте конструктор ...
BookStore::BookStore(const std::string &name) : name_{name} {
  // валидация аргумента
  if (name.empty()) {
    throw std::invalid_argument("BookStore::name must not be empty");
  }
  BookStore::name_ = name;
  BookStore::storage_capacity_ = int {kInitStorageCapacity};
  BookStore::storage_ = new Book[kInitStorageCapacity];

  // здесь мог бы быть ваш сотрясающий землю и выделяющий память код ...
}

// 3. реализуйте деструктор ...
BookStore::~BookStore() {
  // здесь мог бы быть ваш высвобождающий разум от негатива код ...
  // Tip 1: я свободен ..., словно память в куче: не забудьте обнулить указатель
  delete [] BookStore::storage_;
  BookStore::storage_ = {nullptr};
  BookStore::storage_size_ = {0};
  BookStore::storage_capacity_ = {0};
}

// 4. реализуйте метод ...
void BookStore::AddBook(const Book &book) {
  if (storage_size_ == storage_capacity_) {
      ResizeStorageStatus result = resize_storage(BookStore::storage_, BookStore::GetSize(), BookStore::storage_capacity_ + kCapacityCoefficient);
      if (result != ResizeStorageStatus::SUCCESS) {
          return;
      } else {
          BookStore::storage_capacity_ = storage_capacity_ + kCapacityCoefficient;
      }
    // здесь мог бы быть ваш умопомрачительный код ...
    // Tip 1: используйте функцию resize_storage_internal, задав новый размер хранилища
    // Tip 2: не забудьте обработать статус вызова функции
  }

  BookStore::storage_[storage_size_] = book;
  BookStore::storage_size_++;

  // Tip 3: не забудьте добавить книгу в наше бездонное хранилище ...
}

// РЕАЛИЗОВАНО

const std::string &BookStore::GetName() const {
  return name_;
}

int BookStore::GetSize() const {
  return storage_size_;
}

int BookStore::GetCapacity() const {
  return storage_capacity_;
}

const Book *BookStore::GetBooks() const {
  return storage_;
}

ResizeStorageStatus BookStore::resize_storage_internal(int new_capacity) {
  // изменяем размеры хранилища с копированием старых данных в хранилище нового объема
  const ResizeStorageStatus status = resize_storage(storage_, storage_size_, new_capacity);

  // если все прошло ОК, то сохраняем новый объем хранилища в объекте
  if (status == ResizeStorageStatus::SUCCESS) {
    storage_capacity_ = new_capacity;
  }

  return status;
}