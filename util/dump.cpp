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
   leveldb::Status s = leveldb::DB::Open(options, path, &db);
   if (!s.ok()) {
      cerr << "ERROR: failed opening database: " << s.ToString() << endl;
      return 111;
   }

   leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
   for (it->SeekToFirst(); it->Valid(); it->Next()) {
      cout << it->key().ToString() << '\t' << it->value().ToString() << endl;
      if (!it->status().ok()) {
         cerr << "ERROR: error during iteration: " << s.ToString() << endl;
         return 111;
      }
   }
   delete it;

   delete db;

   return 0;
}
 