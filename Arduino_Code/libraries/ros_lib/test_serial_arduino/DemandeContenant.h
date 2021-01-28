#ifndef _ROS_SERVICE_DemandeContenant_h
#define _ROS_SERVICE_DemandeContenant_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace test_serial_arduino
{

static const char DEMANDECONTENANT[] = "test_serial_arduino/DemandeContenant";

  class DemandeContenantRequest : public ros::Msg
  {
    public:

    DemandeContenantRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return DEMANDECONTENANT; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class DemandeContenantResponse : public ros::Msg
  {
    public:
      typedef int64_t _code_type;
      _code_type code;
      typedef bool _success_type;
      _success_type success;

    DemandeContenantResponse():
      code(0),
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_code;
      u_code.real = this->code;
      *(outbuffer + offset + 0) = (u_code.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_code.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_code.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_code.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_code.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_code.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_code.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_code.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->code);
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_code;
      u_code.base = 0;
      u_code.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_code.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_code.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_code.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_code.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_code.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_code.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_code.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->code = u_code.real;
      offset += sizeof(this->code);
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return DEMANDECONTENANT; };
    const char * getMD5(){ return "1fba6e229d5c61f74155aa006ab7b7e3"; };

  };

  class DemandeContenant {
    public:
    typedef DemandeContenantRequest Request;
    typedef DemandeContenantResponse Response;
  };

}
#endif
