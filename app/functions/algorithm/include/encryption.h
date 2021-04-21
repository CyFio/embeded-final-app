/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:45:55 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: encryption.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QString>

struct EncyptConfig{
    int key;
};

QString Encypt(const QString& source, const EncyptConfig&);

QString Decypt(const QString& source, const EncyptConfig&);

#endif // ENCRYPTION_H
