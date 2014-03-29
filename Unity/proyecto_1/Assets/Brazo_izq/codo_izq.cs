/**
*  @file brazo_izq.cs
*  @brief PFC de Jorge Regidor - UAH  
* 
*  Imprime los movimientos en el codo izquierdo
* 
*  @author Jorge Regidor
*  @date 10/2013
*  @Version 1.0
*/


/// Importamos librerias
using UnityEngine;
using System.Collections;

/// Creamos la clase
public class codo_izq : MonoBehaviour {
	
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
	transform.rotation = Quaternion.Slerp (transform.rotation, gui.q4 , gui.speed * Time.deltaTime);
	} // final update
} // final clase
