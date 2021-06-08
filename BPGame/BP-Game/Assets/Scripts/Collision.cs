using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class Collision : MonoBehaviour
{
    [SerializeField] private TextMeshProUGUI TMPtext;
    [SerializeField] private TextMeshProUGUI YouWon;
    public bool isRight;
    int i;

    void OnCollisionEnter2D(Collision2D col)
    {
        i++;
        if (i == 5 && isRight) {  YouWon.gameObject.SetActive(true); }
        else if(i == 5) { YouWon.SetText("YOU LOST");  YouWon.gameObject.SetActive(true); }

        if (isRight)
        {
            SingletonInt.Instance.setRight(i);
            TMPtext.SetText(i.ToString() + "/" + SingletonInt.Instance.left.ToString());
        }
        else {
            SingletonInt.Instance.setLeft(i);
            TMPtext.SetText( SingletonInt.Instance.right.ToString() + "/" + i.ToString());
        }
        col.gameObject.GetComponent<BallClick>().ResetPos();
    }
}
