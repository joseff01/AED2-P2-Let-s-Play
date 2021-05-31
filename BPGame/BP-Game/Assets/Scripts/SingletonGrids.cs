using System;
using UnityEngine;


public class SingletonGrids{
    private static SingletonGrids instance;
    public Vector3[] globalGrid;
    public Vector2[] globalFrogGrid;


    public static SingletonGrids Instance
    {
        get
        {
            if (instance == null)
                instance = new SingletonGrids();
            return instance;
        }
    }
    public void setGlobalGrid(Vector3[] grid)
    {
        globalGrid = grid;

    }
    public void setGlobalFrogGrid(Vector2[] grid)
    {
        globalFrogGrid = grid;
    }

    public void asignZValues()
    {
        arrayZValue(globalFrogGrid,1);
        Vector2[] canchas = { new Vector2(-5.5f, 0.5f), new Vector2(4.5f, 0.5f) };
        arrayZValue(canchas, 2);
    }
    void arrayZValue(Vector2[] arrayV2, float value)
    {
        foreach (Vector2 element in arrayV2)
        {
            Vector3 position = Array.Find(globalGrid, gridPos => ((Vector2)gridPos).Equals(element));
            int index = Array.IndexOf(globalGrid, position);
            position.z = value;
            globalGrid[index] = position;
        }
    }
    public void  ballPos(Vector3 pos)
    {
        bool flag = true;
        foreach (Vector3 gridPos in globalGrid)
        {
            int index = Array.IndexOf(globalGrid, gridPos);

            if(flag && ((gridPos - pos).sqrMagnitude < 1))
            {
                globalGrid[index].z = 3;
                flag = false;
            }
            else if (gridPos.z ==3)
            {
                globalGrid[index].z = 0;
                
            }
        }
        createMatrix();
    }
    void createMatrix()
    {
        int[,] matrix = new int[11, 7];
        int counter = 0;
        for (int y = 0; y < matrix.GetLength(1); y += 1)
        {
            for (int x = 0; x < matrix.GetLength(0); x += 1)
            {
                matrix[x, y] = (int)globalGrid[counter].z;
                counter++;
            }
        }
        PrintMatrix(matrix);
        SendMatrixJson.serializeMatrix(matrix);
    }


    void PrintMatrix(int[,] matrix)
    {
        int rowLength = matrix.GetLength(0);
        int colLength = matrix.GetLength(1);
        string arrayString = "";
        for (int j = 0; j < colLength; j++)
        {
            for (int i = 0; i < rowLength; i++)
            {
                arrayString += string.Format("{0} ", matrix[i, j]);
            }
            arrayString += System.Environment.NewLine + System.Environment.NewLine;
        }

        Debug.Log(arrayString);
    }
}
        
