package org.acz.leveldb;

import com.google.common.base.Charsets;
import com.google.common.io.Files;
import org.testng.Assert;
import org.testng.annotations.Test;

import java.io.File;

public class TestLevelDbNative
{
    @Test
    public void testLevelDbNative()
            throws LevelDbException
    {
        LevelDbNative db = LevelDbNative.create(Files.createTempDir());

        byte[] key = bytes("hello");
        byte[] value = bytes("world");

        db.put(key, value);
        Assert.assertEquals(db.get(key), value);
        db.delete(key);

        db.put(key, value);

        db.close();
    }

    @Test(expectedExceptions = LevelDbException.class)
    public void testCreateFailsIfExists()
            throws LevelDbException
    {
        File dir = Files.createTempDir();

        try {
            LevelDbNative.create(dir).close();
        }
        catch (LevelDbException e) {
            Assert.fail("first create failed", e);
        }

        LevelDbNative.create(dir);
    }

    @Test
    public void testUpdateOpensExisting()
            throws LevelDbException
    {
        File dir = Files.createTempDir();
        LevelDbNative.create(dir).close();
        LevelDbNative.update(dir).close();
    }

    @Test(expectedExceptions = LevelDbException.class)
    public void testUpdateFailsIfNotExists()
            throws LevelDbException
    {
        LevelDbNative.update(Files.createTempDir());
    }

    @Test
    public void testCreateOrUpdateCreatesNew()
            throws LevelDbException
    {
        LevelDbNative.createOrUpdate(Files.createTempDir()).close();
    }

    @Test
    public void testCreateOrUpdateOpensExisting()
            throws LevelDbException
    {
        File dir = Files.createTempDir();
        LevelDbNative.create(dir).close();
        LevelDbNative.createOrUpdate(dir).close();
    }

    private static byte[] bytes(String s)
    {
        return s.getBytes(Charsets.UTF_8);
    }
}
