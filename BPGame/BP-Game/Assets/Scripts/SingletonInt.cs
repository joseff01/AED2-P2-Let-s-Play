using UnityEngine;
public class SingletonInt
{
    private static SingletonInt instance;
    public int value;
    public BPClient client;
    public int right = 0;
    public int left = 0;
    public bool isPlayer = false;
    public bool isPlayerMult = false;
    public bool isMultiPlayer = false;

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
    public void setRight(int value)
    {
        right = value;
    }
    public void setLeft(int value)
    {
        left = value;
    }
    public void setPlayer(bool value)
    {
        isPlayer = value;
    }
}