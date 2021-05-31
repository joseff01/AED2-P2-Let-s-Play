using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DrawPredictiveLine : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    void DrawLine(int[,] mapMatrix)
    {
        gridWidth = 7;
        gridHeight = 11;
        tileWidth = 1;
        tileHeight = 1;

        int counter = 1;
        bool drawing = true;
        bool foundFirst = false;
        bool foundSecond = false;
        Vector3 firstPoint;
        Vector3 secondPoint;

        while (drawing)
        {
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    if (mapMatrix[i][j] == counter)
                    {
                        Vector3 firstPoint = new Vector3(j * gridWidth / 7 + tileWidth / 2, i * gridHeight / 11 + tileHeight / 2, 0);
                        foundFirst = true;
                    }
                    if (mapMatrix[i][j] == counter + 1)
                    {
                        Vector3 secondPoint = new Vector3(j * gridWidth / 7 + tileWidth / 2, i * gridHeight / 11 + tileHeight / 2, 0);
                        foundSecond = true;
                    }
                }
            }
            if (foundFirst && foundSecond)
            {
                Debug.DrawLine(firstPoint, secondPoint, Color.red, 5);
                counter++;
                foundFirst = false;
                foundSecond = false;
            }
            else
            {
                drawing = false;
                return;
            }

        }
    }
}
