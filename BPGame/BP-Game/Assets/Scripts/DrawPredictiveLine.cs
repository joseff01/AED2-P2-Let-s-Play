using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

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
        bool foundNext = false;

        //For creating line renderer object
        LineRenderer lineRenderer = new GameObject("Line").AddComponent<LineRenderer>();
        lineRenderer.startColor = Color.red;
        lineRenderer.endColor = Color.red;
        lineRenderer.startWidth = 0.1f;
        lineRenderer.endWidth = 0.1f;
        lineRenderer.positionCount = mapMatrix.Cast<int>().Max();
        lineRenderer.useWorldSpace = true;

        while (drawing)
        {
            Vector3 firstPoint = new Vector3(123123, 1231231, 1231231);
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    if (mapMatrix[i, j] == counter)
                    {
                        firstPoint = new Vector3(j * gridWidth / 7 + (float)tileWidth / 2f - 5.5f, i * gridHeight / 11 + (float)tileHeight / 2f - 3.5f, -10);
                        foundNext = true;
                    }
                }
            }

            if (foundNext)
            {
                lineRenderer.SetPosition(0, firstPoint);
                counter++;
                foundNext = false;
            }
            else
            {
                drawing = false;
                return;
            }

        }
    }
}
