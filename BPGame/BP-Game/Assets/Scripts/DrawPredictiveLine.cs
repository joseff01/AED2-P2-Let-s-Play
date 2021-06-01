using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class DrawPredictiveLine : MonoBehaviour
{

    public static void DrawLine(int[,] mapMatrix)
    {
        int gridWidth = 11;
        int gridHeight = 7;
        int tileWidth = 1;
        int tileHeight = 1;

        int counter = 1;
        bool drawing = true;
        bool foundFirst = false;
        bool foundSecond = false;

        while (drawing)
        {
            Vector3 firstPoint = new Vector3(123123,1231231,1231231);
            Vector3 secondPoint = new Vector3(1312313, 1235345, 534536); ;
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    if (mapMatrix[i,j] == counter)
                    {
                        firstPoint = new Vector3(j * gridWidth / 7 + tileWidth / 2, i * gridHeight / 11 + tileHeight / 2, 0);
                        foundFirst = true;
                    }
                    if (mapMatrix[i,j] == counter + 1)
                    {
                        secondPoint = new Vector3(j * gridWidth / 7 + tileWidth / 2, i * gridHeight / 11 + tileHeight / 2, 0);
                        foundSecond = true;
                    }
                }
            }

            if (foundFirst && foundSecond)
            {
                Gizmos.DrawLine(firstPoint, secondPoint);
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
