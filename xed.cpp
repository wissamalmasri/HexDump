#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <cctype>

using namespace std;

enum OutputFormat {
 HEX,
 BINARY
};

void printHex(char byte) {
 cout << setw(2) << setfill('0') << nouppercase << hex << (int)(unsigned char)byte;
}

void printBinary(char byte) {
 for (int i = 7; i >= 0; --i) {
  cout << ((byte >> i) & 1);
  }
}

void printByte(char byte) {
 if (isprint(byte)) {
  cout << byte;
  } else {
 cout << ".";
  }
}

void printFormattedOutput(const char *buffer, int size, OutputFormat format) {
 for (int i = 0; i < size; ++i) {
 if (i % 8 == 0) {
 if (i != 0) {
 cout << " ";
 for (int j = i - 8; j < i; ++j) {
 printByte(buffer[j]);
 }
 cout << endl;
 }
 cout << setw(8) << setfill('0') << hex << i << ": ";
 }
 if (format == HEX)
 printHex(buffer[i]);
 else if (format == BINARY)
 printBinary(buffer[i]);
 cout << " "; 
 }
 int remaining = size % 8;
 if (remaining > 0) {
 cout << " ";
 for (int i = size - remaining; i < size; ++i) {
 printByte(buffer[i]);
   }
 }
 cout << endl;
}

int main(int argc, char *argv[]) {
 if (argc < 2) {
  cerr << "Usage: " << argv[0] << " [-b] <filename>" << endl;
   return 1;
 }

 bool binaryFormat = false;
 const char *filename;
 if (argc == 2) {
 filename = argv[1];
 } else if (argc == 3 && strcmp(argv[1], "-b") == 0) {
 binaryFormat = true;
 filename = argv[2];
 } else {
 cerr << "Usage: " << argv[0] << " [-b] <filename>" << endl;
  return 1;
   }

 ifstream file(filename, ios::binary);
 if (!file) {
  cerr << "Error opening file: " << filename << endl;
  return 1;
  }

 char buffer[8];
 OutputFormat format = binaryFormat ? BINARY : HEX;
  int count = 0;

 while (file.read(buffer, sizeof(buffer))) {
 printFormattedOutput(buffer, file.gcount(), format);
 count += file.gcount();
  }
  if (file.gcount() > 0) {
  printFormattedOutput(buffer, file.gcount(), format);
  }
  cout << endl;
  file.close();
  return 0;
}
