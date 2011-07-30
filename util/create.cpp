#include <iostream>
#include <fstream>
#include <unistd.h>
#include "leveldb/db.h"

using namespace std;

int main(int argc, char *argv[])
{
   if (argc != 2) {
      cerr << "usage: create DATABASE_PATH" << endl;
      return 100;
   }
   const char *path = argv[1];

   leveldb::DB* db;
   leveldb::Options options;
   options.create_if_missing = true;
   options.error_if_exists = true;
   leveldb::Status s = leveldb::DB::Open(options, path, &db);
   if (!s.ok()) {
      cerr << "ERROR: failed opening database: " << s.ToString() << endl;
      return 111;
   }

   string line;
   while (getline(cin, line)) {
      size_t i = line.find('\t');
      if (i == string::npos) {
         cerr << "ERROR: no tab separator in input line" << endl;
         return 100;
      }
      string key = line.substr(0, i);
      string value = line.substr(i + 1);

      s = db->Put(leveldb::WriteOptions(), key, value);
      if (!s.ok()) {
         cerr << "ERROR: database put failed: " << s.ToString() << endl;
         return 111;
      }
   }

   delete db;

   return 0;
}
 