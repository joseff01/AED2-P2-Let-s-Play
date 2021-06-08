using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class multiplayerScript : MonoBehaviour
{
    public void changeIsMultiplayer()
    {
        if (SingletonInt.Instance.isMultiPlayer)
            SingletonInt.Instance.isMultiPlayer = false;
        else
            SingletonInt.Instance.isMultiPlayer = true; 
    }

}
