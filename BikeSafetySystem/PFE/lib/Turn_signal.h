//
// Created by Antoine on 02/12/2016.
//

#ifndef TURN_SIGNAL_H
#define TURN_SIGNAL_H

/*!
 * \file Turn_signal.h
 * \brief Turn signal manager
 * \author AUGAY Antoine
 * \version 0.1
 */

#include "GPIO_manager.h"

/*! Left / Right enum */
enum L_R_enum {
    NONE /*!< No turn signal */
   ,LEFT    /*!< Left value */
   ,RIGHT   /*!< Right value */
};

/*! \class Turn_signal
   * \brief classe de gestion des clignotants
   *
   */
class Turn_signal {
private:

    GPIO_manager gpio;         /*!< reference of a GPIO_manager object*/
    int pin_left_turn_signal;  /*!< pin of the left turn signal*/
    int pin_right_turn_signal; /*!< pin of the left turn signal*/
    L_R_enum active_signal;    /*!< turn signal currently working, { 'L' for left, 'R' for right, 'N' for nothing }*/
    bool signal_state;         /*!< state of the turn signals (on or off) */

public:

    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Turn_signal
     *
     *  \param pin_left_signal : pin of the left turn signal
     *  \param pin_right_signal : pin of the right turn signal
     *  \param gpio : reference of GPIO_manger object
     */
    Turn_signal(int pin_left_signal, int pin_right_signal, GPIO_manager& gpio);

	/*!
     *  \brief initialisation function
     *
     *  Set pin_left_turn_signal and pin_right_turn_signal as output mode
     *  Set those two pin at default value (turn signal off)
     *
     *  \param nothing
     *  \return nothing
     */
    void init();
	
    /*!
     *  \brief Change a turn signal state
     *
     *  \param pos : left or right turn signal
     *  \param state : 1 or 0 (0 : turn signal off)
     *  \return nothing
     */
    void set_turn_signal(L_R_enum pos, bool state);

    /*!
     *  \brief Change a turn signal state
     *
     *  \param pos : left or right turn signal
     *  \param state : 1 or 0 (0 : turn signal off)
     *  \return nothing
     */
    void toggle_turn_signal(void);

    /*!
      *  \brief Change a active signal
      *
      *  \param new_active_signal : signal which is currently working
      *  \return nothing
      */
    void set_active_signal(L_R_enum new_active_signal){
        active_signal = new_active_signal;
    }

    /*!
      *  \brief Reset turn signal
      *
      *  \param nothing
      *  \return nothing
      */
	  void reset_state_signal();

    /*!
      *  \brief TEMPO
      *
      *  \param new_active_signal : signal which is currently working
      *  \return nothing
      */

};


#endif //TURNSIGNAL_TURN_SIGNAL_H
