#ifndef BENCHMARK_H
#define BENCHMARK_H


#define LENGTH 6
//STANDARD MESSAGE

 char *two_char_msg = "12\n";

 char *ten_char_msg = "1234567890\n";

 char *thirty_char_msg = "123456789012345678901234567890\n";

 char *fifty_char_msg = "12345678901234567890123456789012345678901234567890\n";

 char *seventy_char_msg = "1234567890123456789012345678901234567890123456789012345678901234567890\n";

 char *hundred_char_msg = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\n";

int msg_array_length = 6;
char *messages[LENGTH];
extern void initMsg();

//ESCAPE SEQUENCE

  const char *escape = "~";

#endif
