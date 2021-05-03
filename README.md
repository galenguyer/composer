# Composer

A simple C program to make managing several docker-compose files easier.

## Usage/Examples

Composer finds your `docker-compose.yaml` file as well as any `docker-compose.*.yaml` files and passes them to `docker-compose`.

`composer up -d` and `docker-compose -f docker-compose.yaml [-f docker-compose.*.yaml] up -d` are equivalent.

## Deployment

To deploy this project run `sudo make install`. This will compile and install the composer binary. You can then run any docker-compose command with composer.
  
## Environment Variables

Composer passes the current environment to docker-compose when run. As such, you can run `COMPOSE_VARIABLE=value composer` and expect the same behavior as `COMPOSE_VARIABLE=value docker-compose`.

## License

[MIT](https://choosealicense.com/licenses/mit/)
