// Generated by gencpp from file test_serial_arduino/DemandeContenant.msg
// DO NOT EDIT!


#ifndef TEST_SERIAL_ARDUINO_MESSAGE_DEMANDECONTENANT_H
#define TEST_SERIAL_ARDUINO_MESSAGE_DEMANDECONTENANT_H

#include <ros/service_traits.h>


#include <test_serial_arduino/DemandeContenantRequest.h>
#include <test_serial_arduino/DemandeContenantResponse.h>


namespace test_serial_arduino
{

struct DemandeContenant
{

typedef DemandeContenantRequest Request;
typedef DemandeContenantResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct DemandeContenant
} // namespace test_serial_arduino


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::test_serial_arduino::DemandeContenant > {
  static const char* value()
  {
    return "1fba6e229d5c61f74155aa006ab7b7e3";
  }

  static const char* value(const ::test_serial_arduino::DemandeContenant&) { return value(); }
};

template<>
struct DataType< ::test_serial_arduino::DemandeContenant > {
  static const char* value()
  {
    return "test_serial_arduino/DemandeContenant";
  }

  static const char* value(const ::test_serial_arduino::DemandeContenant&) { return value(); }
};


// service_traits::MD5Sum< ::test_serial_arduino::DemandeContenantRequest> should match 
// service_traits::MD5Sum< ::test_serial_arduino::DemandeContenant > 
template<>
struct MD5Sum< ::test_serial_arduino::DemandeContenantRequest>
{
  static const char* value()
  {
    return MD5Sum< ::test_serial_arduino::DemandeContenant >::value();
  }
  static const char* value(const ::test_serial_arduino::DemandeContenantRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::test_serial_arduino::DemandeContenantRequest> should match 
// service_traits::DataType< ::test_serial_arduino::DemandeContenant > 
template<>
struct DataType< ::test_serial_arduino::DemandeContenantRequest>
{
  static const char* value()
  {
    return DataType< ::test_serial_arduino::DemandeContenant >::value();
  }
  static const char* value(const ::test_serial_arduino::DemandeContenantRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::test_serial_arduino::DemandeContenantResponse> should match 
// service_traits::MD5Sum< ::test_serial_arduino::DemandeContenant > 
template<>
struct MD5Sum< ::test_serial_arduino::DemandeContenantResponse>
{
  static const char* value()
  {
    return MD5Sum< ::test_serial_arduino::DemandeContenant >::value();
  }
  static const char* value(const ::test_serial_arduino::DemandeContenantResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::test_serial_arduino::DemandeContenantResponse> should match 
// service_traits::DataType< ::test_serial_arduino::DemandeContenant > 
template<>
struct DataType< ::test_serial_arduino::DemandeContenantResponse>
{
  static const char* value()
  {
    return DataType< ::test_serial_arduino::DemandeContenant >::value();
  }
  static const char* value(const ::test_serial_arduino::DemandeContenantResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // TEST_SERIAL_ARDUINO_MESSAGE_DEMANDECONTENANT_H