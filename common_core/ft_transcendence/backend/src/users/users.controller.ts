import { Controller, Get, Post, Body, Patch, Param, Delete, ExecutionContext, UseGuards, Request, Response, Headers } from '@nestjs/common';
import { UsersService } from './users.service';
import { CreateUserDto } from '../auth/dto/create-user.dto';
import { UpdateUserDto } from './dto/update-user.dto';
import { AuthGuard } from '../auth/auth.guard';
import { request } from 'http';
import { JwtAuthGuard } from 'src/auth/guard/jwt.guard';

@Controller('users')
export class UsersController {
  constructor(private readonly usersService: UsersService, private authguard: AuthGuard) {}

  @Post()
  async create(@Body() createUserDto: CreateUserDto) {
    return this.usersService.create(createUserDto);
  }

  @Get()
  @UseGuards(JwtAuthGuard)
  findAll() {
    return this.usersService.findAll();
  }

  @Get('me')
  @UseGuards(JwtAuthGuard)
  async findMe(@Request() req) {
    const id = parseInt(req.user.id);
    return this.usersService.findMe(id);
  }

  @Get(':id')
  @UseGuards(JwtAuthGuard)
  findOne(@Param('id') id: string) {
    const numericId = parseInt(id, 10);
    return this.usersService.findOneByID(numericId);
  }
  
  @Patch('me')
  @UseGuards(JwtAuthGuard)
  update(@Request() req, @Body() updateUserDto: UpdateUserDto) {
    const id = parseInt(req.user.id);
    console.log("updateUserDto", updateUserDto);
    return this.usersService.update(+id, updateUserDto);
  }
  
  @Delete(':id')
  @UseGuards(JwtAuthGuard)
  remove(@Param('id') id: string) {
    return this.usersService.remove(+id);
  }

  @Get(':id/stats')
  @UseGuards(JwtAuthGuard)
  getStats(@Param('id') id: string) {
    return this.usersService.getStats(+id);
  }
}
