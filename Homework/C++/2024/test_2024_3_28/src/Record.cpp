#include "../include/Record.h"

#include <cstring>

Record::Record() {
  strcpy(_name, "None");
  strcpy(_relation, "None");
}

Record::Record(const char *name, const char *relation) {
  strcpy(_name, name);
  strcpy(_relation, relation);
}

void Record::set_name(const char *name) { strcpy(_name, name); }

void Record::set_relation(const char *relation) { strcpy(_relation, relation); }

const char *Record::get_name() const { return _name; }

const char *Record::get_relation() const { return _relation; }

void Record::set_tele(const char *tele) { strcpy(_tele, tele); }

const char *Record::get_tele() const { return _tele; }
