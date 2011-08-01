#include "LevelDbNative.h"
#include "leveldb/db.h"
#include <assert.h>
#include <stdio.h>

static void setStatusString(JNIEnv *env, jobject obj, leveldb::Status status);
static void setDatabaseHandle(JNIEnv *env, jobject obj, leveldb::DB *db);
static leveldb::DB *getDatabaseHandle(JNIEnv *env, jobject obj);
static std::string *byteArrayToString(JNIEnv *env, jobject obj, jbyteArray array);

JNIEXPORT jboolean JNICALL Java_org_acz_leveldb_LevelDbNative_open0
    (JNIEnv *env, jobject obj, jstring pathParam, jboolean create, jboolean exclusive)
{
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = create;
    options.error_if_exists = exclusive;

    const char *path = env->GetStringUTFChars(pathParam, NULL);
    leveldb::Status status = leveldb::DB::Open(options, path, &db);
    env->ReleaseStringUTFChars(pathParam, path);

    if (!status.ok()) {
        setStatusString(env, obj, status);
        return false;
    }

    setDatabaseHandle(env, obj, db);
    return true;
}

JNIEXPORT void JNICALL Java_org_acz_leveldb_LevelDbNative_close0
    (JNIEnv *env, jobject obj)
{
    leveldb::DB *db = getDatabaseHandle(env, obj);
    if (db == NULL) {
        delete db;
        setDatabaseHandle(env, obj, NULL);
    }
}

JNIEXPORT jbyteArray JNICALL Java_org_acz_leveldb_LevelDbNative_get0
    (JNIEnv *env, jobject obj, jbyteArray keyParam)
{
    leveldb::DB *db = getDatabaseHandle(env, obj);
    if (db == NULL) {
        return NULL;
    }

    std::string *key = byteArrayToString(env, obj, keyParam);
    std::string value;
    leveldb::Status status = db->Get(leveldb::ReadOptions(), *key, &value);
    delete key;

    if (!status.ok()) {
        setStatusString(env, obj, status);
        return NULL;
    }

    jbyteArray array = env->NewByteArray(value.size());
    if (array != NULL) {
        env->SetByteArrayRegion(array, 0, value.size(), (jbyte *) value.data());
    }
    return array;
}

JNIEXPORT jboolean JNICALL Java_org_acz_leveldb_LevelDbNative_put0
    (JNIEnv *env, jobject obj, jbyteArray keyParam, jbyteArray valueParam)
{
    leveldb::DB *db = getDatabaseHandle(env, obj);
    if (db == NULL) {
        return false;
    }

    std::string *key = byteArrayToString(env, obj, keyParam);
    std::string *value = byteArrayToString(env, obj, valueParam);
    leveldb::Status status = db->Put(leveldb::WriteOptions(), *key, *value);
    delete key;
    delete value;

    if (!status.ok()) {
        setStatusString(env, obj, status);
        return false;
    }

    return true;
}

JNIEXPORT jboolean JNICALL Java_org_acz_leveldb_LevelDbNative_delete0
    (JNIEnv *env, jobject obj, jbyteArray keyParam)
{
    leveldb::DB *db = getDatabaseHandle(env, obj);
    if (db == NULL) {
        return false;
    }

    std::string *key = byteArrayToString(env, obj, keyParam);
    leveldb::Status status = db->Delete(leveldb::WriteOptions(), *key);
    delete key;

    if (!status.ok()) {
        setStatusString(env, obj, status);
        return false;
    }

    return true;
}

static void setStatusString(JNIEnv *env, jobject obj, leveldb::Status status)
{
    jstring str = env->NewStringUTF(status.ToString().c_str());

    jclass cls = env->GetObjectClass(obj);
    jfieldID fid = env->GetFieldID(cls, "statusString", "Ljava/lang/String;");
    if (fid != NULL) {
        env->SetObjectField(obj, fid, str);
    }
}

static void setDatabaseHandle(JNIEnv *env, jobject obj, leveldb::DB *db)
{
    jclass cls = env->GetObjectClass(obj);
    jfieldID fid = env->GetFieldID(cls, "handle", "J");
    if (fid != NULL) {
        env->SetLongField(obj, fid, (long) db);
    }
}

static leveldb::DB *getDatabaseHandle(JNIEnv *env, jobject obj)
{
    jclass cls = env->GetObjectClass(obj);
    jfieldID fid = env->GetFieldID(cls, "handle", "J");
    if (fid != NULL) {
        return (leveldb::DB *) env->GetLongField(obj, fid);
    }
    return NULL;
}

static std::string *byteArrayToString(JNIEnv *env, jobject obj, jbyteArray array)
{
    jint len = env->GetArrayLength(array);
    jbyte *bytes = (jbyte *) env->GetPrimitiveArrayCritical(array, NULL);
    if (bytes == NULL) {
        return NULL;
    }
    std::string *s = new std::string((char *) bytes, len);
    env->ReleasePrimitiveArrayCritical(array, bytes, 0);
    return s;
}
