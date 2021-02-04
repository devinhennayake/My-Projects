#ifndef DS_EXCEPTIONS_H
#define DS_EXCEPTIONS_H
#include <string>

class UnderflowException {

public:
  UnderflowException();
  UnderflowException(std::string message){
    _message = message;
  }
  virtual const std::string what() const throw()
  {
    return _message ;
  }
private:
  std::string _message;
};
/*
class IllegalArgumentException {
  
public:
  IllegalArgumentException();
  IllegealArgumentException(std::string message){
    _message = message; }
  virtual const std::string what() const throw()
  {
    return _message ; }
private:
  std::string _message;
};


class ArrayIndexOutOfBoundsException {

public:
  ArrayIndexOutOfBoundsException();
  ArrayIndexOutOfBoundsException(std::string message){
    _message = message;
  }
  virtual const std::string what() const throw(){
    return _message; }
private:
  std::string _message;

};
class IteratorOutOfBoundsException {

public:
  IteratorOutOfBoundsException();
  IteratorOutOfBoundsException(std::string message){
    _message = message; }
  
  virtual const std::string what() const throw(){
    return _message; }
private:
  std::string _message;
};
class IteratorMismatchException {

public:
  IteratorMismatchException();
  IteratorMismatchException(std::string message){
    _message = message; }
  
  virtual const std::string what() const throw(){
    return _message; }
private:
  std::string _message;
};
class IteratorUninitializedException {

public:
  IteratorUninitializedException();
  IteratorUninitializedException(std::string message){
    _message = message; }
  
  virtual const std::string what() const throw(){
    return _message; }
private:
  std::string _message;
};
*/

#endif
