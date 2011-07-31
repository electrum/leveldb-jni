package org.acz.leveldb;

import java.io.File;
import java.util.Iterator;

public class LevelDbNative
        implements LevelDb
{
    static {
        System.load(new File("libleveldbnative.so").getAbsolutePath());
    }

    private long handle;

    private String statusString;

    private native boolean open0(String path);

    private native void close0();

    private native byte[] get0(byte[] key);

    private native boolean put0(byte[] key, byte[] value);

    private native boolean delete0(byte[] key);

    public LevelDbNative(File path)
            throws LevelDbException
    {
        if (!open0(path.getAbsolutePath())) {
            System.out.println(statusString);
            throw new LevelDbException(statusString);
        }
    }

    @Override
    public void close()
            throws LevelDbException
    {
        close0();
    }

    @Override
    public byte[] get(byte[] key)
            throws LevelDbException
    {
        byte[] value = get0(key);
        if (value == null) {
            throw new LevelDbException(statusString);
        }
        return value;
    }

    @Override
    public void put(byte[] key, byte[] value)
            throws LevelDbException
    {
        if (!put0(key, value)) {
            throw new LevelDbException(statusString);
        }
    }

    @Override
    public void delete(byte[] key)
            throws LevelDbException
    {
        if (!delete0(key)) {
            throw new LevelDbException(statusString);
        }
    }

    @Override
    public void writeBatch(WriteBatch batch)
            throws LevelDbException
    {
        throw new UnsupportedOperationException();
    }

    @Override
    public Iterator<Entry> iterator()
    {
        throw new UnsupportedOperationException();
    }

    @Override
    public Iterator<Entry> iterator(byte[] keyStart)
    {
        throw new UnsupportedOperationException();
    }
}
