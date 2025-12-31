

function print(value) {
    console.log(value)
}


// test_instance.htvm
var Player_health = 100;
var Player_mana = 50;
var hero_health = 100;
var hero_mana = 50;
var goblin_health = 100;
var goblin_mana = 50;
async function main() {
    hero_health = 200;
    goblin_health = 30;
    print("Hero health is: " + hero_health);
    print("Goblin health is: " + goblin_health);
    

}
main();