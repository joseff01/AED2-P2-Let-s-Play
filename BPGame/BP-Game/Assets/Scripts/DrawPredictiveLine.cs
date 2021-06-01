using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

public class DrawPredictiveLine : MonoBehaviour
{
    public GameObject points;
    
    public void Start()
    {
        Invoke("TrynDraw", 0.1f);
    }
    void TrynDraw() {
        int[,] matriz = new int[7, 11] { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 5, 4, 3, 2, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
        draw(matriz);
    }

    public void draw(int[,] mapMatrix)
    {
        int counter = 0;
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 11; j++)
            {
                if (mapMatrix[i, j] != 0)
                {
                    Debug.Log(SingletonGrids.Instance.globalGrid[counter]);
                    Instantiate(points, SingletonGrids.Instance.globalGrid[counter], Quaternion.identity);
                }
                counter++;
            }
        }

    }

}
