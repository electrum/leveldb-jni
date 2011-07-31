package org.acz.leveldb;

import com.google.common.base.Charsets;
import com.google.common.io.Files;
import org.testng.Assert;
import org.testng.annotations.Test;

public class TestLevelDbNative
{
    @Test
    public void testLevelDbNative()
            throws LevelDbException
    {
        LevelDbNative db = new LevelDbNative(Files.createTempDir());

        byte[] key = bytes("hello");
        byte[] value = bytes("world");

        db.put(key, value);
        Assert.assertEquals(db.get(key), value);
        db.delete(key);

        db.put(key, value);

        db.close();
    }

    private static byte[] bytes(String s)
    {
        return s.getBytes(Charsets.UTF_8);
    }
}
