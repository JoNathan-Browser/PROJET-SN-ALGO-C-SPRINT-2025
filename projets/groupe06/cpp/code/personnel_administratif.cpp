#include "personnel_administratif.hpp"
#include "includes.hpp"
#include "medecin.hpp"
#include "patient.hpp"
 

personnel_administratif::personnel_administratif(std::string nom):medecin(nom)
{
    //ici on a utilisé le constructeur de la classe medecin en faisant :medecin(nom)
}



void personnel_administratif::marquer_facture_paye( patient& p, double facture)
{
    p.payer_facture(facture);
}




void personnel_administratif::enregistrer_patient(patient p,std::list<patient>& liste_patients)//meme pour signaler qu'on passe par reference on le fait une seule fois dans le .hpp
{
    liste_patients.push_back(p);
}

 




void personnel_administratif::sauvegarder_donne_patient(patient p)
{
    namespace fs = std::filesystem;
    

    std::string dossier = "./patients/";
    std::string chemin = dossier + p.matricule_patient + ".txt";

    // Vérifie si le dossier existe, sinon le crée
    if (!fs::exists(dossier)) {
        fs::create_directories(dossier); // Crée tous les dossiers nécessaires
    }

    std::ofstream file(chemin);//ouvre le fichier pour stoquer les informations 
    
    if (!file.good()) return;
    
    if(file.is_open())
    {
        int num{1};
        std::vector<std::variant<std::string, int , char ,feuille_medicale>> vect=p.get_dossier_medical();

        std::string nom_patient{ std::get<std::string>(vect[0]) };
        int age_patient{ std::get<int>(vect[1]) };
        char sexe_patient{ std::get<char>(vect[2]) };
        
        file<<"nom du patient:"<<nom_patient<<" age: "<<age_patient<<" sexe: "<<sexe_patient<<std::endl;

        for (auto it = vect.begin() + 3; it != vect.end(); ++it) 
        {
            auto tmp = *it;
            try
            {
                file<<" CONSULTATION NUMERO: "<<num<<"\n";
                file<<"    nom du medecin de la consultation: "<< std::get<feuille_medicale>(tmp).nom_medecin  <<"\n";
                file<<"    date et heure de la consultation: "<<std::get<feuille_medicale>(tmp).date_heure<<"\n";
                file<<"    Diagnostique établie ce jour : "<<std::get<feuille_medicale>(tmp).diagnostique<<"\n";
                file<<"    facture de la consultation: "<<std::get<feuille_medicale>(tmp).facture<<"\n";
                num++;
            } catch (const std::bad_variant_access&) //capturer une erreur de type du variant
            {
                // Ce n'était pas une feuille médicale, donc on ignore
            }
        }

        if(!p.rappels.empty())
        {
            auto copie = p.rappels;
            file<<"        vos rappels:"<<std::endl;
            while (!copie.empty()) 
            {
                file<<"             "<<copie.top() << std::endl;
                copie.pop();
            }
        }
        file<<"Facture a payer en tout: "<<p.consulter_facture();
        file.close();//pas necessaire de fermer le fichier mais ne derange pas 
    }
    else{std::cout<<"erreur d'ouverture du fichier\n";}

    
}

//std::string message = std::format("Bonjour {}, tu as {} ans.", name, age);
