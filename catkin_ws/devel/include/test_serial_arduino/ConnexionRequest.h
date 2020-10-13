// Generated by gencpp from file test_serial_arduino/ConnexionRequest.msg
// DO NOT EDIT!


#ifndef TEST_SERIAL_ARDUINO_MESSAGE_CONNEXIONREQUEST_H
#define TEST_SERIAL_ARDUINO_MESSAGE_CONNEXIONREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace test_serial_arduino
{
template <class ContainerAllocator>
struct ConnexionRequest_
{
  typedef ConnexionRequest_<ContainerAllocator> Type;

  ConnexionRequest_()
    {
    }
  ConnexionRequest_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> const> ConstPtr;

}; // struct ConnexionRequest_

typedef ::test_serial_arduino::ConnexionRequest_<std::allocator<void> > ConnexionRequest;

typedef boost::shared_ptr< ::test_serial_arduino::ConnexionRequest > ConnexionRequestPtr;
typedef boost::shared_ptr< ::test_serial_arduino::ConnexionRequest const> ConnexionRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace test_serial_arduino

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::test_serial_arduino::ConnexionRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "test_serial_arduino/ConnexionRequest";
  }

  static const char* value(const ::test_serial_arduino::ConnexionRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
";
  }

  static const char* value(const ::test_serial_arduino::ConnexionRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ConnexionRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::test_serial_arduino::ConnexionRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::test_serial_arduino::ConnexionRequest_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // TEST_SERIAL_ARDUINO_MESSAGE_CONNEXIONREQUEST_H
