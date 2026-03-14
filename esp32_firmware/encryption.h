#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "base64.h"

/*
 Base64 encoding used as encryption layer
 Converts message into encoded text so
 network payload is not readable directly
*/

String encryptMessage(String msg)
{
  String encoded = base64::encode(msg);
  return encoded;
}

#endif