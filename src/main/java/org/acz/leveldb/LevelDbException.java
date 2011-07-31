package org.acz.leveldb;

import java.io.IOException;

public class LevelDbException
        extends IOException
{
    public LevelDbException()
    {
    }

    public LevelDbException(String message)
    {
        super(message);
    }

    public LevelDbException(String message, Throwable cause)
    {
        super(message, cause);
    }

    public LevelDbException(Throwable cause)
    {
        super(cause);
    }
}
