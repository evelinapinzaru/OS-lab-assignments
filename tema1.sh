#!/bin/bash

opt=0
while [ $opt -ne 1 ]
do
  echo -e "\nPress ENTER to continue..."
  read dummy

  clear
  echo -e "Optiuni :\n"
  echo "1 --> iesire"
  echo "2 --> afisare"
  echo "3 --> when is XMAS comin' ?"
  echo "4 --> afisarea primelor 2 shell-uri instalate in sistem"
  echo "5 --> afisarea datelor despre toti utilizatorii din sistem"
  echo "6 --> afisarea ultimelor linii incepand cu a 9-a din fisierul \"/etc/protocols\""
  echo "7 --> afisare tip procesor si marimea cache-lui"
  echo "8 --> afisarea tuturor folderelor din directorul \"/proc\" care nu reprezinta imaginea unui proces pe disc"
  echo "9 --> afisarea tuturor fisierelor de log si afisarea liniilor dintr-un fisier log dat ce contin un text dat"

  echo -ne "\nIntroduceti numarul optiunii dorite : "
  read opt

  case $opt in
    1) break;;

    2) echo -e "\nID-ul procesului initiat la executarea script-ului : $$"
       echo "Tipul sistemului de operare: $(uname)"
       echo "Numarul de secunde de cand s-a executat script-ul : $SECONDS sec"
       echo "Calea curenta : $PWD";;

    3) nr_sapt=$(date -d "December 25" +%V)
       zi_sapt=$(date -d "December 25" +%A)
       echo -e "\nCraciunul va fi in ziua de $zi_sapt a saptamanii cu numarul"\
               "$nr_sapt a anului curent.";; 

    4) echo -e  "\nPrimele 2 shell-uri instalate in sistem : "
       head -n 2 /etc/shells;; 

    5) awk -F ':' '{print "\nNume de login: " $1 " | user ID : " $3 " | nume complet : " $5 " | directorul de home : " $6}' /etc/passwd;;

    6) echo -e "\n"
       tail -n +9 /etc/protocols;;

    7) tip_procesor=$(grep "model name" /proc/cpuinfo | uniq | sed 's/model name[[:space:]]*: //')
       marime_cache=$(grep "cache size" /proc/cpuinfo | uniq | sed 's/cache size[[:space:]]*: //')  
       echo -e "\nTip procesor: $tip_procesor"
       echo "Mărime cache: $marime_cache";;  

    8) ls -l /proc | grep '^d' | grep -vE '^[0-9]+$';;

    9) echo -e "\nFișiere de log:\n"
       ls *.log
       gunzip -c *.log

       #functie ce afiseaza liniile din fisierul fisier_log ce contin text_cautat 
       afisare_linii() {
         fisier_log=$1
         text_cautat=$2

         grep "$text_cautat" "$fisier_log"
       }

       echo -e "Introduceti numele fisierului de log :"
       read log_file
       echo -e "Introduceti textul ce va fi cautat :"
       read searched_text

       afisare_linii "$log_file" "$searched_text";;

    *) echo -e "\nPlease enter a number between 1 and 9 next time you run this script !";;

  esac

sleep 1
done
