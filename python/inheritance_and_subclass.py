
class Unit(object):
    def __init__(self, rank, size, life):
        self.name = self.__class__.__name__
        self.rank = rank
        self.size = size
        self.life = life

    def show_status(self):
        print('name : {}'.format(self.name))
        print('rank : {}'.format(self.rank))
        print('size : {}'.format(self.size))
        print('life : {}'.format(self.life))

class Goblin(Unit):
    def __init__(self, rank, size, life, attack_type, damage):
        super(Goblin, self).__init__(rank, size, life)
        self.attack_type = attack_type
        self.damage = damage

    def show_status(self):
        super(Goblin, self).show_status()
        print('attack_type : {}'.format(self.attack_type))
        print('damage : {}'.format(self.damage))

    def attack(self):
        print('{} is attacking, damage {}'.format(self.name, self.damage))

class SphereGoblin(Goblin):
    def __init__(self, rank, size, life, attack_type, damage, sphere_type):
        super(SphereGoblin, self).__init__(rank, size, life, attack_type, damage);
        self.sphere_type = sphere_type

    def show_status(self):
        super(SphereGoblin, self).show_status()
        print('sphere type : {}'.format(self.sphere_type))

class Hero(Unit):
    def __init__(self, rank, size, life, goblins=None):
        super(Hero, self).__init__(rank, size, life)
        if (goblins is None):
            self.goblins = []
        else:
            self.goblins = goblins

    def show_own_goblins(self):
        num_of_goblins = len([x for x in self.goblins if isinstance(x, Goblin)])
        num_of_sphere_goblins = len([x for x in self.goblins if isinstance(x, SphereGoblin)])
        print('goblis {}, sphere goblins {}'.format(num_of_goblins, num_of_sphere_goblins))

    def make_goblin_attack(self):
        for goblin in self.goblins:
            goblin.attack()

    def add_goblins(self, new_goblins):
        for goblin in new_goblins:
            if goblin not in self.goblins:
                self.goblins.append(goblin)
            else:
                print('goblin {} is already exist'.format(goblin))

    def remove_goblins(self, old_goblins):
        for goblin in old_goblins:
            try:
                self.goblins.remove(goblin)
            except:
                print('goblin {} is not exist'.format(goblin))


goblin_1 = Goblin('soldier', 'small', 100, 'melee', 15)
goblin_2 = Goblin('soldier', 'small', 100, 'melee', 15)
sphere_goblin_1 = SphereGoblin('soldier', 'small', 100, 'range', 10, 'long')

hero_1 = Hero('hero', 'big', 300, [goblin_1, goblin_2, sphere_goblin_1])

goblin_3 = Goblin('soldier', 'small', 100, 'melee', 20)
sphere_goblin_2 = SphereGoblin('soldier', 'small', 100, 'range', 5, 'long')

goblin_4 = Goblin('soldier', 'small', 100, 'melee', 30)

print('# before adding goblins')
hero_1.show_own_goblins()
hero_1.make_goblin_attack()

hero_1.add_goblins([goblin_3, sphere_goblin_2])

print('# after adding goblins')
hero_1.show_own_goblins()
hero_1.make_goblin_attack()

hero_1.remove_goblins([goblin_3, sphere_goblin_2])

print('# after removing goblins')
hero_1.show_own_goblins()
hero_1.make_goblin_attack()

hero_1.remove_goblins([goblin_4])
