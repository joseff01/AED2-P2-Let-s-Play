using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GetMatrix : MonoBehaviour
{
    // Start is called before the first frame update
    public static void sendMessage() {
        int i = SingletonInt.Instance.value;
        Debug.Log("matrix");
    }

}
