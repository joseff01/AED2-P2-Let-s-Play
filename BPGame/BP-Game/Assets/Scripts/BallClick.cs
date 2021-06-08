using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/**
 * @brief BallClick clase que detecta el click de la bola y realiza el movimiento del objeto
 * */
public class BallClick : MonoBehaviour
{
    [SerializeField] private Transform[] points;
    [SerializeField] private LineController line;
    [SerializeField] private GameObject ball;

    Rigidbody2D rb;
    Vector3 startingPos;

    public GameObject indicator;
    private bool clicked = false;

    public bool reset = false;
    bool first = true;


    private void Start()                     //Obtiene el Rigid Body
    {
        rb = GetComponent<Rigidbody2D>();
        startingPos = gameObject.transform.position;
        Invoke("ResetPos", 0.5f);
    }

    private void OnMouseDown()              //Detecta Click del mouse    
    {
        if (SingletonInt.Instance.isPlayer)
        {
            rb.isKinematic = true;                                                                      // Permite que la bola no se mueva
            clicked = true;
            line.setVIsible(true);
        }
    }
    private void OnMouseUp()               //Detecta release del mouse
    {
        if (SingletonInt.Instance.isPlayer)
        {
            clicked = false;
            indicator.SetActive(false);
            line.setVIsible(false);

            pushBall();
        }
    }
    private void Update()                  //Mueve el indicador a la posicion del mouse
    {
        if (clicked)
        {
            Vector3 mouseCast = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            indicator.transform.position = new Vector3(mouseCast.x, mouseCast.y, 0);
            indicator.SetActive(true);                                                              // Hace visible al indicador
            line.SetupLine(points);
        }
    }

    private void pushBall()
    {
        rb.isKinematic = false;                                                                    //Permite que la bola se muevaa

        Vector2 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        Vector2 ballPos = gameObject.transform.position;


        rb.AddRelativeForce(mousePos - ballPos, ForceMode2D.Impulse);

        StartCoroutine(callStop());
    }

    IEnumerator callStop()
    {
        yield return new WaitForSeconds(1);
        if (reset)
        {
            reset = false;
            rb.velocity = Vector3.zero;
            rb.angularVelocity = 0;
        }
        else
            StartCoroutine(stopMotion());  //Para el movimiento de la bola 
    }

    IEnumerator stopMotion()                //Para y hace una llamada al servidor
    {
        rb.velocity = Vector3.zero;
        rb.angularVelocity = 0;
        SingletonGrids.Instance.changePlayer();

        yield return new WaitForSeconds(0.2f);
        SingletonGrids.Instance.ballPos(transform.position);
        

    }

    public void ResetPos()  // al colisionar con la cancha se resetea la posicion
    {
        gameObject.transform.position = startingPos;
        rb.velocity = Vector3.zero;
        rb.angularVelocity = 0;
        reset = true;
        StartCoroutine(stopMotion());
        if (first)
        { reset = false;
            first = false;
        }
    }

    public void moveEnemyBall(int[,] mapMatrix) //crea el movimiento del enemigo
    {
        int counter = 0;
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 11; j++)
            {
                if (mapMatrix[i, j] == 2)
                {
                    Vector2 pos = SingletonGrids.Instance.globalGrid[counter];
                    Vector2 ballPos = gameObject.transform.position;
                    rb.AddRelativeForce(pos - ballPos, ForceMode2D.Impulse);
                    break;
                }
                counter++;

            }

        }
        StartCoroutine(callStop());
    }

}


