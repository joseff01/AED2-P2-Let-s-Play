using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallClick : MonoBehaviour
{
    [SerializeField] private Transform[] points;
    [SerializeField] private LineController line;
    [SerializeField] private GameObject ball;
    Rigidbody2D rb;
    public GameObject indicator;
    private bool clicked = false;
    private void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }
    private void OnMouseDown()
    {
        rb.isKinematic = true;
        clicked = true;
        line.setVIsible(true);
        
    }

    private void pushBall()
    {
        rb.isKinematic = false;
        Vector3 mouseCast = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        Vector2 pos = new Vector2(mouseCast.x, mouseCast.y);
        rb.AddForce(pos, ForceMode2D.Impulse);
        

    }

    private void OnMouseUp()
    { 
        clicked = false;
        indicator.SetActive(false);
        line.setVIsible(false);
        pushBall();
    }
    private void Update()
    {
        placeIndicator();
    }
    private void placeIndicator() {
        if(clicked == true){
            Vector3 mouseCast = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            indicator.transform.position = new Vector3(mouseCast.x, mouseCast.y, 0);
            indicator.SetActive(true);
            line.SetupLine(points);
        }
    }
}
