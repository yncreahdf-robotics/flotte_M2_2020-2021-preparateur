
(cl:in-package :asdf)

(defsystem "test_serial_arduino-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Connexion" :depends-on ("_package_Connexion"))
    (:file "_package_Connexion" :depends-on ("_package"))
    (:file "DemandeContenant" :depends-on ("_package_DemandeContenant"))
    (:file "_package_DemandeContenant" :depends-on ("_package"))
    (:file "test" :depends-on ("_package_test"))
    (:file "_package_test" :depends-on ("_package"))
  ))