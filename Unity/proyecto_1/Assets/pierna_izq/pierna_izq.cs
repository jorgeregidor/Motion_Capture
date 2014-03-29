

/**
*  @file pierna_izq.cs
*  @brief PFC de Jorge Regidor - UAH  
* 
*  Imprime los movimientos en la pierna izquierda
* 
*  @author Jorge Regidor
*  @date 10/2013
*  @Version 1.0
*/


/// Importamos librerias
using UnityEngine;
using System.Collections;

/// Creamos la clase
public class pierna_izq : MonoBehaviour {

// ================================================================
// ===                         START                            ===
// ================================================================
	void Start () {
	
	} // final start
	
// ================================================================
// ===                         UPDATE                           ===
// ================================================================
	void Update () {
	
		/// Imprime los valores a la velocidad determinada
		transform.rotation = Quaternion.Slerp (transform.rotation, gui.q6 , gui.speed * Time.deltaTime);
	} // final update
	
} // final clase
