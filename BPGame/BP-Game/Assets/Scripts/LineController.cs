 using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LineController : MonoBehaviour
{
    private LineRenderer lr;
    private Transform[] points;
    private bool isEnabled = false;

    private void Awake()
    {
        lr = GetComponent<LineRenderer>();
    }
    public void SetupLine(Transform[] points)
    {
        lr.positionCount = points.Length;
        this.points = points;
    }
    public void setVIsible(bool active) {
        lr.enabled = active;
        isEnabled = active;

    }
    private void Update()
    {
        if (isEnabled)
        {
            for (int i = 0; i < points.Length; i++)
            {
                lr.SetPosition(i, points[i].position);
            }
        }
    }
}
