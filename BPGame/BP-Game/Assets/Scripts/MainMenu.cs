using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenu : MonoBehaviour
{
    public void PlayGame()
    {
        DrawPredictiveLine.InstantiateLineRenderer();
        Debug.Log(SingletonInt.Instance.isMultiPlayer);
        SingletonInt.Instance.client.StartClient();
        SceneManager.LoadScene(1);
    }

}
