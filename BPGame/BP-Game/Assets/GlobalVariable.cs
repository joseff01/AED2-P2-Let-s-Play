using UnityEngine;
public class GlobalVariable
{
    private static GlobalVariable instance;
    public int value;

    public static GlobalVariable Instance
    {
        get
        {
            if (instance == null)
                instance = new GlobalVariable();
            return instance;
        }
    }
}