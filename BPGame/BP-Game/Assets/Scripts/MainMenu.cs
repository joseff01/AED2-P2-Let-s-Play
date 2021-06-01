using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenu : MonoBehaviour
{
    public void PlayGame()
    {
        DrawPredictiveLine.InstantiateLineRenderer();
        SingletonInt.Instance.client.StartClient();
        SceneManager.LoadScene(1);
    }

}
