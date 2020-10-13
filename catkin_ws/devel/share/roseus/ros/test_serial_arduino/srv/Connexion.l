;; Auto-generated. Do not edit!


(when (boundp 'test_serial_arduino::Connexion)
  (if (not (find-package "TEST_SERIAL_ARDUINO"))
    (make-package "TEST_SERIAL_ARDUINO"))
  (shadow 'Connexion (find-package "TEST_SERIAL_ARDUINO")))
(unless (find-package "TEST_SERIAL_ARDUINO::CONNEXION")
  (make-package "TEST_SERIAL_ARDUINO::CONNEXION"))
(unless (find-package "TEST_SERIAL_ARDUINO::CONNEXIONREQUEST")
  (make-package "TEST_SERIAL_ARDUINO::CONNEXIONREQUEST"))
(unless (find-package "TEST_SERIAL_ARDUINO::CONNEXIONRESPONSE")
  (make-package "TEST_SERIAL_ARDUINO::CONNEXIONRESPONSE"))

(in-package "ROS")





(defclass test_serial_arduino::ConnexionRequest
  :super ros::object
  :slots ())

(defmethod test_serial_arduino::ConnexionRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass test_serial_arduino::ConnexionResponse
  :super ros::object
  :slots (_success ))

(defmethod test_serial_arduino::ConnexionResponse
  (:init
   (&key
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _success __success)
   self)
  (:success
   (&optional __success)
   (if __success (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass test_serial_arduino::Connexion
  :super ros::object
  :slots ())

(setf (get test_serial_arduino::Connexion :md5sum-) "358e233cde0c8a8bcfea4ce193f8fc15")
(setf (get test_serial_arduino::Connexion :datatype-) "test_serial_arduino/Connexion")
(setf (get test_serial_arduino::Connexion :request) test_serial_arduino::ConnexionRequest)
(setf (get test_serial_arduino::Connexion :response) test_serial_arduino::ConnexionResponse)

(defmethod test_serial_arduino::ConnexionRequest
  (:response () (instance test_serial_arduino::ConnexionResponse :init)))

(setf (get test_serial_arduino::ConnexionRequest :md5sum-) "358e233cde0c8a8bcfea4ce193f8fc15")
(setf (get test_serial_arduino::ConnexionRequest :datatype-) "test_serial_arduino/ConnexionRequest")
(setf (get test_serial_arduino::ConnexionRequest :definition-)
      "
---
bool success

")

(setf (get test_serial_arduino::ConnexionResponse :md5sum-) "358e233cde0c8a8bcfea4ce193f8fc15")
(setf (get test_serial_arduino::ConnexionResponse :datatype-) "test_serial_arduino/ConnexionResponse")
(setf (get test_serial_arduino::ConnexionResponse :definition-)
      "
---
bool success

")



(provide :test_serial_arduino/Connexion "358e233cde0c8a8bcfea4ce193f8fc15")


