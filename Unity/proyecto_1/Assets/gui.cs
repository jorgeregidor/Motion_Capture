/**
*  @file gui.cs
*  @brief PFC de Jorge Regidor - UAH
* 
* Programa que recoge los valores del puerto serie y los guarda en
* las variables globales para que otros escript los cojan. Tambien
* Imprime los valores por pantalla y crea un Slider para poder 
* la camara.
* 
*  @author Jorge Regidor
*  @date 10/2013
*  @Version 1.0
*/

/// Importamos librerias

using UnityEngine;
using System.Collections;
using System.IO.Ports;

/// Declaramos la clase
public class gui : MonoBehaviour 
{
	/// Declaramos las variables globales para los quaterniones
	 
	static public Quaternion q0;
	static public Quaternion q1;
	static public Quaternion q2;
	static public Quaternion q3;
	static public Quaternion q4;
	static public Quaternion q5;
	static public Quaternion q6;
	static public Quaternion q7;
	static public Quaternion q8;
	static public Quaternion q9;
	static public Quaternion qA;
	static public Quaternion qB;
	
	/// Declaramos otras variables globales
	
	static public string valu;
	static public float speed=11;
	

	
	/// Declaramos el puerto serie
	SerialPort sp = new SerialPort("COM1",115200); //57600
	
	
	
	// Otras variables

	bool VerDatos = true; ///< variables de la que depende mostrar los valores por pantalla
	float pos_cam = 0; ///< Posicion de la camara
	float seno = 0; ///< valor que ayuda al movimiento de camara
	float coseno=1; ///< valor que ayuda al movimiento de camara
	float angu = 0; ///< Angulo de la Camara
	float acer = 30; ///< Distancia de la camara al modelo 3D
	
	
// ================================================================
// ===                         Start                            ===
// ================================================================

	
	void Start () {
		
	sp.Open();
    sp.ReadTimeout = 50;
	
	} // final Start
	
// ================================================================
// ===                         UPDATE                           ===
// ================================================================

	void Update () {
		
	 /// Recogemos los valores y los guardamos en las variables globales
		try 
			{
				
				 valu = sp.ReadLine(); //leemos la informacion
    		    string[] vec3 = valu.Split(','); // la guardamos en un vector separando los datos por comas
    			
				q0.w= float.Parse (vec3[0]);
				q0.z= -(float.Parse (vec3[1]));
				q0.x= (float.Parse (vec3[2]));
				q0.y= -(float.Parse (vec3[3]));
			
				q1.w= float.Parse (vec3[4]);
				q1.z= -(float.Parse (vec3[5]));
				q1.x= (float.Parse (vec3[6]));
				q1.y= -(float.Parse (vec3[7]));
			
			
				q2.w= float.Parse (vec3[8]);
				q2.z= -(float.Parse (vec3[9]));
				q2.x= (float.Parse (vec3[10]));
				q2.y= -(float.Parse (vec3[11]));
			
			
			
			
				q3.w= float.Parse (vec3[12]);
				q3.z= float.Parse (vec3[13]);
				q3.x= -(float.Parse (vec3[14]));
				q3.y= -(float.Parse (vec3[15]));
			
			    q4.w= float.Parse (vec3[16]);
				q4.z= (float.Parse (vec3[17]));
				q4.x= -(float.Parse (vec3[18]));
				q4.y= -(float.Parse (vec3[19]));
			
			  	q5.w= float.Parse (vec3[20]);
				q5.z= (float.Parse (vec3[21]));
				q5.x= -(float.Parse (vec3[22]));
				q5.y= -(float.Parse (vec3[23]));
			    
			
			
				q6.w= float.Parse (vec3[24]);
				q6.x= float.Parse (vec3[25]);
				q6.z=(float.Parse (vec3[26]));
				q6.y=-(float.Parse (vec3[27]));
			
			    q7.w= float.Parse (vec3[28]);
				q7.x= (float.Parse (vec3[29]));
				q7.z= (float.Parse (vec3[30]));
				q7.y=-(float.Parse (vec3[31]));
			
			  	q8.w= float.Parse (vec3[32]);
				q8.z= (float.Parse (vec3[33]));
				q8.x=(float.Parse (vec3[34]));
				q8.y= -(float.Parse (vec3[35]));
			
			    q9.w= float.Parse (vec3[36]);
				q9.x= (float.Parse (vec3[37]));
				q9.z= (float.Parse (vec3[38]));
				q9.y= -(float.Parse (vec3[39]));
			
			    qA.w= float.Parse (vec3[40]);
				qA.x=(float.Parse (vec3[41]));
				qA.z= (float.Parse (vec3[42]));
				qA.y= -(float.Parse (vec3[43]));
			
			  	qB.w= float.Parse (vec3[44]);
				qB.x= (float.Parse (vec3[45]));
				qB.z= (float.Parse (vec3[46]));
				qB.y= -(float.Parse (vec3[47]));
			
			
			
			sp.BaseStream.Flush(); // limpiamos el buffer
			
				
			
			} // final Try
			catch (System.Exception) // miramos si hay excepciones
			{
			
			} // final Catch
		
		
		
		
	/// Si pulsamos espacio muestra los datos o los quita 	
	if(Input.GetKeyDown(KeyCode.Space))
		{
			if (VerDatos)
			{VerDatos=false;
				acer=20;}
			else
			{VerDatos=true;
			acer = 30;}
			
			
		} // final if
	
	
	/// Valores para el calculo de la posicion y angulo de la camara
		
	seno = acer* Mathf.Sin (pos_cam);	
	coseno =acer * Mathf.Cos (pos_cam);	
	transform.position = new Vector3 (seno, 0,coseno); 	
	
    angu = pos_cam * 180 / Mathf.PI;
		
	transform.eulerAngles = new Vector3 (0, 180+angu,0); 	
	
			
			
		
	} //Final Update
	
	
	
// ================================================================
// ===                         ONGUI                            ===
// ================================================================
	
	
	public void OnGUI()
	{
		/// Mostramos los datos conviertiendo los quaterniones en Angulos de Euler
		if (VerDatos)
		{	
			GUI.Box (new Rect(30,50,200,100),"BRAZO DER");
		 	GUI.Label (new Rect(60,100,200,50),"x="+Mathf.FloorToInt(q0.eulerAngles.y));
			GUI.Label (new Rect(110,100,200,50),"y="+Mathf.FloorToInt(q0.eulerAngles.x));  
			GUI.Label (new Rect(160,100,200,50),"z="+Mathf.FloorToInt(q0.eulerAngles.z));  
			
			GUI.Box (new Rect(30,150,200,100),"CODO DER");
		 	GUI.Label (new Rect(60,200,200,150),"x="+Mathf.FloorToInt(q1.eulerAngles.y));
			GUI.Label (new Rect(110,200,200,150),"y="+Mathf.FloorToInt(q1.eulerAngles.x));  
			GUI.Label (new Rect(160,200,200,150),"z="+Mathf.FloorToInt(q1.eulerAngles.z)); 
			
			GUI.Box (new Rect(30,250,200,100),"MANO DER");
		 	GUI.Label (new Rect(60,300,200,250),"x="+Mathf.FloorToInt(q2.eulerAngles.y));
			GUI.Label (new Rect(110,300,200,250),"y="+Mathf.FloorToInt(q2.eulerAngles.x));  
			GUI.Label (new Rect(160,300,200,250),"z="+Mathf.FloorToInt(q2.eulerAngles.z)); 
		
			GUI.Box (new Rect(30,350,200,100),"PIERNA DER");
		 	GUI.Label (new Rect(60,400,200,250),"x="+Mathf.FloorToInt(q9.eulerAngles.y));
			GUI.Label (new Rect(110,400,200,250),"y="+Mathf.FloorToInt(q9.eulerAngles.x));  
			GUI.Label (new Rect(160,400,200,250),"z="+Mathf.FloorToInt(q9.eulerAngles.z)); 
			
			GUI.Box (new Rect(30,450,200,100),"RODILLA DER");
		 	GUI.Label (new Rect(60,500,200,250),"x="+Mathf.FloorToInt(qA.eulerAngles.y));
			GUI.Label (new Rect(110,500,200,250),"y="+Mathf.FloorToInt(qA.eulerAngles.x));  
			GUI.Label (new Rect(160,500,200,250),"z="+Mathf.FloorToInt(qA.eulerAngles.z)); 
			
		    GUI.Box (new Rect(30,550,200,100),"TRONCO");
		 	GUI.Label (new Rect(60,600,200,250),"x="+Mathf.FloorToInt(qB.eulerAngles.y));
			GUI.Label (new Rect(110,600,200,250),"y="+Mathf.FloorToInt(qB.eulerAngles.x));  
			GUI.Label (new Rect(160,600,200,250),"z="+Mathf.FloorToInt(qB.eulerAngles.z)); 
			
			
			
			GUI.Box (new Rect(Screen.width-230,50,200,100),"BRAZO IZQ");
		 	GUI.Label (new Rect(Screen.width-200,100,200,50),"x="+ Mathf.FloorToInt(q3.eulerAngles.y));
			GUI.Label (new Rect(Screen.width-150,100,200,50),"y="+Mathf.FloorToInt(q3.eulerAngles.x));  
			GUI.Label (new Rect(Screen.width-100,100,200,50),"z="+Mathf.FloorToInt(q3.eulerAngles.z));  
			
		    GUI.Box (new Rect(Screen.width-230,150,200,100),"CODO IZQ");
		 	GUI.Label (new Rect(Screen.width-200,200,200,50),"x="+ Mathf.FloorToInt(q4.eulerAngles.y));
			GUI.Label (new Rect(Screen.width-150,200,200,50),"y="+Mathf.FloorToInt(q4.eulerAngles.x));  
			GUI.Label (new Rect(Screen.width-100,200,200,50),"z="+Mathf.FloorToInt(q4.eulerAngles.z));  
			
			GUI.Box (new Rect(Screen.width-230,250,200,100),"MANO IZQ");
		 	GUI.Label (new Rect(Screen.width-200,300,200,50),"x="+Mathf.FloorToInt(q5.eulerAngles.y));
			GUI.Label (new Rect(Screen.width-150,300,200,50),"y="+Mathf.FloorToInt(q5.eulerAngles.x));  
			GUI.Label (new Rect(Screen.width-100,300,200,50),"z="+Mathf.FloorToInt(q5.eulerAngles.z));  
		
			GUI.Box (new Rect(Screen.width-230,350,200,100),"PIERNA IZQ");
		 	GUI.Label (new Rect(Screen.width-200,400,200,50),"x="+Mathf.FloorToInt(q6.eulerAngles.y));
			GUI.Label (new Rect(Screen.width-150,400,200,50),"y="+Mathf.FloorToInt(q6.eulerAngles.x));  
			GUI.Label (new Rect(Screen.width-100,400,200,50),"z="+Mathf.FloorToInt(q6.eulerAngles.z));  
			
			GUI.Box (new Rect(Screen.width-230,450,200,100),"RODILLA IZQ");
		 	GUI.Label (new Rect(Screen.width-200,500,200,50),"x="+Mathf.FloorToInt(q7.eulerAngles.y));
			GUI.Label (new Rect(Screen.width-150,500,200,50),"y="+Mathf.FloorToInt(q7.eulerAngles.x));  
			GUI.Label (new Rect(Screen.width-100,500,200,50),"z="+Mathf.FloorToInt(q7.eulerAngles.z));  
			
			GUI.Box (new Rect(Screen.width-230,550,200,100),"PIE IZQ");
		 	GUI.Label (new Rect(Screen.width-200,600,200,50),"x="+Mathf.FloorToInt(q8.eulerAngles.y));
			GUI.Label (new Rect(Screen.width-150,600,200,50),"y="+Mathf.FloorToInt(q8.eulerAngles.x));  
			GUI.Label (new Rect(Screen.width-100,600,200,50),"z="+Mathf.FloorToInt(q8.eulerAngles.z));  
		
		
		/// muestra el slider
		pos_cam = GUI.HorizontalSlider(new Rect(Screen.width/2-200,Screen.height-100,400,30),pos_cam,-Mathf.PI/2,Mathf.PI/2);
			
		} // final IF
	} // final onGui
	
	
	
	
} // final Clase
