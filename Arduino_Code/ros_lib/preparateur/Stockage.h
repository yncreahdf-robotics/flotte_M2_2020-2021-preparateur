#ifndef _ROS_SERVICE_Stockage_h
#define _ROS_SERVICE_Stockage_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace preparateur
{

static const char STOCKAGE[] = "preparateur/Stockage";

  class StockageRequest : public ros::Msg
  {
    public:

    StockageRequest()
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

    const char * getType(){ return STOCKAGE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class StockageResponse : public ros::Msg
  {
    public:
      typedef const char* _stockage_type;
      _stockage_type stockage;
      typedef bool _success_type;
      _success_type success;

    StockageResponse():
      stockage(""),
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_stockage = strlen(this->stockage);
      varToArr(outbuffer + offset, length_stockage);
      offset += 4;
      memcpy(outbuffer + offset, this->stockage, length_stockage);
      offset += length_stockage;
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
      uint32_t length_stockage;
      arrToVar(length_stockage, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_stockage; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_stockage-1]=0;
      this->stockage = (char *)(inbuffer + offset-1);
      offset += length_stockage;
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

    const char * getType(){ return STOCKAGE; };
    const char * getMD5(){ return "fdd4bbce80c2db31ba00b5ea52cf1b2c"; };

  };

  class Stockage {
    public:
    typedef StockageRequest Request;
    typedef StockageResponse Response;
  };

}
#endif
