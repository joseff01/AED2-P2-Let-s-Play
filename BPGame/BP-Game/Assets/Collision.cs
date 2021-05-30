using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class Collision : MonoBehaviour
{
    [SerializeField] private TextMeshProUGUI TMPtext;
    public bool isRight;
    int i;

    void OnCollisionEnter2D(Collision2D col)
    {
        Debug.Log("hello");
        i++;
        if (isRight)
        {
            SingletonInt.Instance.setRight(i);
            TMPtext.SetText(SingletonInt.Instance.left.ToString() + "/" + i.ToString());
        }
        else {
            SingletonInt.Instance.setLeft(i);
            TMPtext.SetText( i.ToString() + "/" + SingletonInt.Instance.right.ToString());
        }
    }
}
