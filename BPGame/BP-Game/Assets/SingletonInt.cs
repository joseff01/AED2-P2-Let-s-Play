using UnityEngine;
public class SingletonInt
{
    private static SingletonInt instance;
    public int value;
    public BPClient client;

    public static SingletonInt Instance
    {
        get
        {
            if (instance == null)
                instance = new SingletonInt();
            return instance;
        }
    }
    private SingletonInt()
    {
        client = new BPClient();
    }
}