using UnityEngine;
using System.Collections;
using System.IO.Ports;

public class pul_cubo : MonoBehaviour {

	public float speed;
	private float amoutToMove;
	
	SerialPort sp = new SerialPort("COM3",9600);
	
	
	
	
	// Use this for initialization
	void Start () {
	
		sp.Open();
		sp.ReadTimeout = 1;
	}
	
	// Update is called once per frame
	void Update () {
		
		amoutToMove = speed * Time.deltaTime;
		
		if(sp.IsOpen)
		{
			try
			{
				MoveObject(sp.ReadByte());
				print(sp.ReadByte());
			}
			catch (System.Exception)
			{
			
			}
		}
		
		
		
		
	
	}
	
	void MoveObject(int Direction)
	{
		
		if (Direction == 1)
		{
			transform.Translate(Vector3.left * amoutToMove, Space.World);
			
		}
		if (Direction == 2)
		{
			transform.Translate(Vector3.right * amoutToMove, Space.World);
			
		}
		
		
		
	}
	
	
}
