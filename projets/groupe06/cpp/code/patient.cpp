#include "includes.hpp"
#include "patient.hpp"




patient::patient(std::string nom_patient, int age_patient,char sexe_patient, std::string nom_medecin, std::string etat_sante)
{
    if(nom_medecin.empty()){nom_medecin="Il sagit d'un enregistrement du patient chez le personnel administratif";}
    feuille_medicale f{nom_medecin,this->definir_date(),etat_sante,0};
    dossier_medical.push_back(nom_patient);
    dossier_medical.push_back(age_patient);
    dossier_medical.push_back(sexe_patient);
    dossier_medical.push_back(f);
    this->definir_matricule();
}

patient::patient()
{
    //
}



std::string patient::definir_date()
{
    //recuperer automatiquement la date de l'ordi pour la consultation
    std::time_t maintenant = std::time(nullptr);
    std::tm* tempsLocal = std::localtime(&maintenant);

    std::ostringstream oss;
    oss << std::put_time(tempsLocal, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}



std::stack<std::string> patient::consulter_rappels()
{
    if(!this->rappels.empty())
    {
        return this->rappels;
    }
    std::stack<std::string> tmp;
    return tmp;
}




void patient::supprimer_rappel()
{
    if(!this->rappels.empty()) 
    {
        this->rappels.pop();
        std::cout<<"Le dernier rappel a bien ete suprime de votre liste de rappel cher patient ";
    }
    else
    {
        std::cout<<"Aucun rappel pour le moment  ";
    }
}



double patient::consulter_facture()
{
    return this->facture;
}

void patient::definir_facture(double Facture)
{
    this->facture=Facture;
}

void patient::payer_facture(double Facture)
{
    if(this->facture<=Facture){this->facture=0;}
    else{this->facture-=Facture;}
}





void patient::definir_matricule()
{
    std::srand(std::time(0));

    // Générer un chiffre (0-9) pour le premier caractère
    this->matricule_patient += '0' + std::rand() % 10;

    // Générer 4 lettres aléatoires (a-z)
    for (int i = 1; i < 5; ++i) {
        this->matricule_patient += 'a' + std::rand() % 26;
    }

    /*
        en effet ici je ne me rassure pas que le matricule rentré ici ne puisse pas etre reproduit
        je me base sur la probabilite que cette methode genere un matricule 2 fois 
        Ainsi, chaque exécution de la fonction a une chance sur 4 569 760 de produire une chaîne spécifique
    */

}




std::vector<std::variant<std::string, int , char ,feuille_medicale>>  patient::get_dossier_medical()
{
    return this->dossier_medical;
}




std::string patient::get_nom_patient()
{
    std::string nom_patient{ std::get<std::string>(this->dossier_medical[0]) };
    return nom_patient;
}






void patient::consulter_dossier_patient()
{
    //medecin est un ami de la classe patient donc il peut utiliser les atributs privés de la classe sans soucis
    if(!this->dossier_medical.empty())
    {
        int num{1};
        std::string nom_patient{ std::get<std::string>(this->dossier_medical[0]) };
        int age_patient{ std::get<int>(this->dossier_medical[1]) };
        char sexe_patient{ std::get<char>(this->dossier_medical[2]) };
        
        std::cout<<" **** nom du patient:"<<nom_patient<<" age: "<<age_patient<<" sexe: "<<sexe_patient<<std::endl;

        std::cout<<"\n####################################################################\n"; 
        for (auto it = this->dossier_medical.begin() + 3; it != this->dossier_medical.end(); ++it) 
        {
            auto tmp = *it;
            try
            {
                std::cout<<"    \nCONSULTATION NUMERO: "<<num<<std::endl;
                std::cout<<"    nom du medecin de la consultation: "<< std::get<feuille_medicale>(tmp).nom_medecin  <<std::endl;
                std::cout<<"    date et heure de la consultation: "<<std::get<feuille_medicale>(tmp).date_heure<<std::endl;
                std::cout<<"    Diagnostique etablie ce jour : "<<std::get<feuille_medicale>(tmp).diagnostique<<std::endl;
                std::cout<<"    facture de la consultation: "<<std::get<feuille_medicale>(tmp).facture;
                num++;
            } catch (const std::bad_variant_access&) //capturer une erreur de type du variant
            {
                // Ce n'était pas une feuille médicale, donc on ignore
            }
        }

        std::cout<<"\n####################################################################\n";
    }
}


