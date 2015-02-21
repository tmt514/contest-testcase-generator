#ifndef _CONSTRAINT_H_
#define _CONSTRAINT_H_

class Constraint
{
  protected:
    static int ID;
    int id;
  public:
    Constraint() { id = ++Constraint::ID; }
    int getID() { return id; }
};

#endif /* _CONSTRAINT_H_ */
