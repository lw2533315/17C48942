/* 
 * File:   generalhashing.h
 * Author: Administrator
 *
 * Created on 2015年11月25日, 下午2:36
 */

#ifndef GENERALHASHING_H
#define	GENERALHASHING_H



#include <string>


typedef unsigned int (*HashFunction)(const std::string&);


unsigned int RSHash  (const std::string& str);
unsigned int JSHash  (const std::string& str);
unsigned int PJWHash (const std::string& str);
unsigned int ELFHash (const std::string& str);
unsigned int BKDRHash(const std::string& str);
unsigned int SDBMHash(const std::string& str);
unsigned int DJBHash (const std::string& str);
unsigned int DEKHash (const std::string& str);
unsigned int BPHash  (const std::string& str);
unsigned int FNVHash (const std::string& str);
unsigned int APHash  (const std::string& str);

#endif	/* GENERALHASHING_H */

