

/**
*  @file pierna_der.cs
*  @brief PFC de Jorge Regidor - UAH  
* 
*  Imprime los movimientos en la pierna derecha
* 
*  @author Jorge Regidor
*  @date 10/2013
*  @Version 1.0
*/


/// Importamos librerias
using UnityEngine;
using System.Collections;

/// creamos la clase
public class pierna_der : MonoBehaviour {

// ================================================================
// ===                         START                            ===
// ================================================================
	void Start () {
	
	} // final start
	
// ================================================================
// ===                         UPDATE                           ===
// ================================================================
	
	void Update () {
	
		/// Imprime los movimientos a la velocidad determinada
	transform.rotation = Quaternion.Slerp (transform.rotation, gui.q9 , gui.speed * Time.deltaTime);
	} // final update
} // final clase
