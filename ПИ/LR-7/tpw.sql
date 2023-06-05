
create table pizzas(
	pizzas_id int not null generated always as identity primary key,
	pizzas_name varchar(255) not null,
	pizzas_calories int not null,
	pizzas_description varchar(255) default 'пицца муцураев'
);

create table weapons(
	weapons_id int not null generated always as identity primary key,
	weapons_name varchar(255) not null,
	weapons_dps int not null
);

create table turtles(
	turtles_id int not null generated always as identity primary key,
	turtles_name varchar(255) not null,
	turtles_color varchar(255) not null,
	turtles_weaponId int not null,
	turtles_favoritePizzaId int not null,
	turtles_secondFavoritePizzaId int not null,
	turtles_image varchar(255) not null,
	constraint fk_weaponId_turtles foreign key (turtles_weaponId) references weapons(weapons_id),
	constraint fk_favoritePizzaId_turtles foreign key (turtles_favoritePizzaId) references pizzas(pizzas_id),
	constraint fk_secondFavoritePizzaId_turtles foreign key (turtles_secondFavoritePizzaId) references pizzas(pizzas_id)
);


insert into pizzas (pizzas_name,pizzas_calories) values ('mozarello', 1000);
insert into pizzas (pizzas_name,pizzas_calories) values ('home', 800);
insert into pizzas (pizzas_name,pizzas_calories) values ('fourseasons', 1200);
insert into pizzas (pizzas_name,pizzas_calories) values ('pesto', 1500);
insert into pizzas (pizzas_name,pizzas_calories) values ('cheese', 400);

insert into weapons (weapons_name,weapons_dps) values ('katana', 200); 
insert into weapons (weapons_name,weapons_dps) values ('daggers-sai', 400); 
insert into weapons (weapons_name,weapons_dps) values ('pole-bo', 250); 
insert into weapons (weapons_name,weapons_dps) values ('nunchaku', 300); 

insert into turtles (turtles_name,turtles_color, turtles_weaponId,turtles_favoritePizzaId, turtles_secondFavoritePizzaId, turtles_image )
values ('Leonardo', 'blue', 1,1,2,'C:\Users\Administrator\Desktop\Домашка\ПИ\LR-7\imagesleonardo.jpg');
insert into turtles (turtles_name,turtles_color, turtles_weaponId,turtles_favoritePizzaId, turtles_secondFavoritePizzaId, turtles_image )
values ('Raphael', 'red', 2,2,3,'C:\Users\Administrator\Desktop\Домашка\ПИ\LR-7\imagesrafael.jpg');
insert into turtles (turtles_name,turtles_color, turtles_weaponId,turtles_favoritePizzaId, turtles_secondFavoritePizzaId, turtles_image )
values ('Donatello', 'purple', 3,3,4,'C:\Users\Administrator\Desktop\Домашка\ПИ\LR-7\imagesdonatelo.jpg');
insert into turtles (turtles_name,turtles_color, turtles_weaponId,turtles_favoritePizzaId, turtles_secondFavoritePizzaId, turtles_image )
values ('Michelangelo', 'orange', 4,4,5,'C:\Users\Administrator\Desktop\Домашка\ПИ\LR-7\imagesmikelangello.jpg');

--new
insert into turtles (turtles_name,turtles_color, turtles_image, turtles_favoritepizzaid, turtles_secondFavoritePizzaId,turtles_weaponId) 
values ('Leonardo', 'blue','C:\Users\Administrator\Desktop\Домашка\ПИ\LR-7\imagesleonardo.jpg',1,1,2);
insert into turtles (turtles_name,turtles_color, turtles_image, turtles_weaponId,turtles_favoritePizzaId, turtles_secondFavoritePizzaId )
values ('Raphael', 'red', 'C:\Users\Administrator\Desktop\Домашка\ПИ\LR-7\imagesrafael.jpg', 2,2,3);
insert into turtles (turtles_name,turtles_color,turtles_image, turtles_weaponId,turtles_favoritePizzaId, turtles_secondFavoritePizzaId )
values ('Donatello', 'purple','C:\Users\Administrator\Desktop\Домашка\ПИ\LR-7\imagesdonatelo.jpg', 3,3,4);
insert into turtles (turtles_name,turtles_color, turtles_image, turtles_weaponId,turtles_favoritePizzaId, turtles_secondFavoritePizzaId )
values ('Michelangelo', 'orange','C:\Users\Administrator\Desktop\Домашка\ПИ\LR-7\imagesmikelangello.jpg', 4,4,5);


drop table if exists pizzas, weapons, turtles;
