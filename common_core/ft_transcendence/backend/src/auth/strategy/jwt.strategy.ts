import {HttpException, HttpStatus, Injectable} from "@nestjs/common";
import {PassportStrategy} from "@nestjs/passport";
import {ExtractJwt, Strategy} from "passport-jwt";
import {ConfigService} from '@nestjs/config';

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy) {
    constructor(
        private configService: ConfigService,
        ) {
            super({
                secretOrKey: configService.get<string>('KEY_JWT'),
                jwtFromRequest: ExtractJwt.fromExtractors([
                    (request) => {
                        return request.headers.authorization.replace('Bearer ', '');
                    },
                ]),
            });
        }
    async validate(payload: any) {
        if (!payload) {
            throw new HttpException('Invalid token', HttpStatus.UNAUTHORIZED);
        }
		// if (payload.twofactor == "need") {
		// 	throw new HttpException('twofactor need' , HttpStatus.UNAUTHORIZED);
		// }
        return { id: payload.id };
    }
}