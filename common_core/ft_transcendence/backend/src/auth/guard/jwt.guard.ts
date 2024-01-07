import { ExecutionContext, Injectable } from "@nestjs/common";
import { AuthGuard } from "@nestjs/passport";
import { AuthService } from "../auth.service";

@Injectable()
export class JwtAuthGuard extends AuthGuard('jwt') {
    constructor(private authService: AuthService) {
        super();
    }
    
    async canActivate(context: ExecutionContext): Promise<boolean> {
       const result = (await super.canActivate(context)) as boolean;
       return result;
    }
}