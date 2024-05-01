# MINISHELL TESTS LOG

## Tests ou on doit etre comme bash

verifier variables d'expansion en argument
anouk	anouk
anouk
echo {1..80}
echo ${anouk}e
echo ${!v\*}
echo $'anuk\n\n\n\n'
echo anouk"anouk"
echo 'anouk'"anouk"
echo "anouk"$a"anou\nyoyo" | cat -e
echo "anouk\"$a\"anou\nyoyo" | cat -e
echo "anouk'$a'anou\nyoyo" | cat -e
plusieurs operateur |||
echo 'a|a'
a"nouk"
"anouk"oo"aa"aa"
ls-la
ls|wc
< wc ls
ls\<wc
cat Makefile|grep src| **bash ouvre heredoc, nous on considere que c comme grep "src|"??**
cat Makefile|grep src

## Tests specifiques a minishell

ls\\|wc (on escape pas le backlash)
ls '\'\<newline\>
echo $'anouk\tanouk\nanouk'
anouk+=$zuzu (on ne modif des param que avec export)
count=$(wc -l <(sort myfile.txt))
for word in $sentence; do echo "Word: $word"; done
echo $"\*" (une seule str, param separes par premier char de IFS variable : "$\*"  is equivalent to "$1c$2c..." & un esp si IFS = unset & pas de sep si IFS est null)

**pour les tests comme ca, c'est utile pour gestion d'erreur: bash accepterait, considererait les carac comme des caracteres speciaux avec expansion etc, pr nous = caractere normal**


tests de separation avant identification (normal que les guillemets soient tjrs là)

a"no"|uk" : fonctionne, 3 words = a"no" | uk"
a"no"'||u'k" : fonctionne, ne donne qu'un seul token


**test ne fonctionne pas** : 
```
"r'tt)"
```





(((command1 && command2) || command3) && (command4 || (command5 && command6)))

