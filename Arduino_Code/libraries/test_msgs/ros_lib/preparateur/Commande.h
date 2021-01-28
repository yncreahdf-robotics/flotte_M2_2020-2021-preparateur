#ifndef _ROS_SERVICE_Commande_h
#define _ROS_SERVICE_Commande_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace preparateur
{

static const char COMMANDE[] = "preparateur/Commande";

  class CommandeRequest : public ros::Msg
  {
    public:
      typedef const char* _com_type;
      _com_type com;

    CommandeRequest():
      com("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_com = strlen(this->com);
      varToArr(outbuffer + offset, length_com);
      offset += 4;
      memcpy(outbuffer + offset, this->com, length_com);
      offset += length_com;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_com;
      arrToVar(length_com, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_com; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_com-1]=0;
      this->com = (char *)(inbuffer + offset-1);
      offset += length_com;
     return offset;
    }

    const char * getType(){ return COMMANDE; };
    const char * getMD5(){ return "48b59ebc92f3c82074ea080d053eaa6d"; };

  };

  class CommandeResponse : public ros::Msg
  {
    public:
      typedef int64_t _code_type;
      _code_type code;
      typedef bool _success_type;
      _success_type success;

    CommandeResponse():
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

    const char * getType(){ return COMMANDE; };
    const char * getMD5(){ return "1fba6e229d5c61f74155aa006ab7b7e3"; };

  };

  class Commande {
    public:
    typedef CommandeRequest Request;
    typedef CommandeResponse Response;
  };

}
#endif
